<?hh // strict

namespace axolotl\entities;

use \axolotl\exceptions\InvalidArgumentException;

/**
 * @Entity
 * @Table(name="modules")
 */
class Module{
  /** @Id @Column(type="integer") @GeneratedValue */
  protected int $id;

  /** @Column(type="text") */
  protected string $vendor;

  /** @Column(type="text") */
  protected string $name;

  /** @ManyToOne(targetEntity="RoutingInfo", inversedBy="module") */
  protected array<RoutingInfo> $routingInfo;

  /** @Column(type="datetimetz", name="installed_at") */
  protected \DateTime $installationDate;

  /** @OneToMany(targetEntity="User", mappedBy="installedModules") */
  protected User $creator;

  public function __construct(){
    $this->id = -1;
    $this->name = "";
    $this->installationDate = new \DateTime(
      "@".time(), new \DateTimeZone("Europe/Berlin")
    );
    $this->vendor = "";
    $this->routingInfo = array();
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

  public function setVendor(string $vendor): void{
    if(strlen($vendor) === 0){
      throw new InvalidArgumentException("Empty vendor");
    }
    $this->vendor = $vendor;
  }
  public function getVendor(): string{
    return $this->vendor;
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

  public function setRoutingInfo(array<RoutingInfo> $info): void{
    $hasRoot = false;
    foreach($info as $i){
      if($i->getURI() === '/'){
        $hasRoot = true;
        break;
      }
    }
    if(!$hasRoot){
      throw new InvalidArgumentException('Module does not provide root');
    }
    $this->routingInfo = $info;
  }
  public function getRoutingInfo(): array<RoutingInfo>{
    return $this->routingInfo;
  }

  public function setCreator(User $creator): void{
    $this->creator = $creator;
  }
  public function getCreator(): User{
    return $this->creator;
  }
}
