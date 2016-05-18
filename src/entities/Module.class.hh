<?hh // strict

namespace axolotl\entities;

require_once __DIR__.'/User.class.hh';
require_once __DIR__.'/../exceptions/InvalidArgumentException.class.hh';

use \axolotl\exceptions\InvalidArgumentException;

/**
 * @Entity
 * @Table(name="modules")
 */
class Module{
  /** @Id @Column(type="integer") @GeneratedValue */
  protected int $id;

  /** @Column(type="text") */
  protected string $name;

  /** @Column(type="datetimetz", name="installed_at") */
  protected \DateTime $installationDate;

  /** @ManyToOne(targetEntity="User", inversedBy="installedModules") */
  protected User $creator;

  public function __construct(){
    $this->id = -1;
    $this->name = "";
    $this->installationDate = new \DateTime(
      "@".time(), new \DateTimeZone("Europe/Berlin")
    );
    $this->creator = new User();
  }

  public static function newInstance(
    string $name, ?\DateTime $installationDate, User $creator
  ): Module{
    $module = new Module();
    $module->setName($name);
    $module->setInstallationDate($installationDate);
    $module->setCreator($creator);
    return $module;
  }

  public function getID(): int{
    return $this->id;
  }

  public function setName(string $name): void{
    $name = trim($name);
    if(strlen($name) === 0){
      throw new InvalidArgumentException("Name is empty");
    }
    $this->name = $name;
  }
  public function getName(): string{
    return $this->name;
  }

  public function setInstallationDate(?\DateTime $installationDate=null): void{
    if($installationDate === null){
      $installationDate = new \DateTime(
        "@".time(), new \DateTimeZone("Europe/Berlin")
      );
    }
    invariant(
      $installationDate !== null, "Module::setInstallDate: installDate is null"
    );
    $this->installationDate = $installationDate;
  }
  public function getInstallationDate(): \DateTime{
    return $this->installationDate;
  }

  public function setCreator(User $creator): void{
    $this->creator = $creator;
  }
  public function getCreator(): User{
    return $this->creator;
  }
}
