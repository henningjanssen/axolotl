<?hh // strict

namespace axolotl\entities;

use \axolotl\exceptions\InvalidArgumentException;
use \Doctrine\Common\Collections\ArrayCollection;
use \Doctrine\Common\Collections\Collection as DoctrineCollection;

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

  /** @Column(type="text") */
  protected string $description;

  /** @Column(type="text") */
  protected string $path;

  /** @OneToMany(targetEntity="RoutingInfo", mappedBy="module") */
  protected DoctrineCollection<RoutingInfo> $routingInfo;

  /** @Column(type="datetimetz", name="installed_at") */
  protected \DateTime $installationDate;

  /** @ManyToOne(targetEntity="User", inversedBy="installedModules") */
  protected User $creator;

  public function __construct(){
    $this->id = -1;
    $this->name = "";
    $this->installationDate = new \DateTime(
      'now', new \DateTimeZone("Europe/Berlin")
    );
    $this->vendor = "";
    $this->path = "";
    $this->description = "";
    $this->routingInfo = new ArrayCollection(array());
    $this->creator = new User();
  }

  public static function newInstance(
    string $vendor, string $name, string $description, string $path,
    ?\DateTime $installationDate, User $creator
  ): Module{
    $module = new Module();
    $module->setVendor($vendor);
    $module->setName($name);
    $module->setDescription($description);
    $module->setPath($path);
    $module->setInstallationDate($installationDate);
    $module->setCreator($creator);
    return $module;
  }

  public function getID(): int{
    return $this->id;
  }

  public function setVendor(string $vendor): Module{
    if(strlen($vendor) === 0){
      throw new InvalidArgumentException("Empty vendor");
    }
    $this->vendor = $vendor;
    return $this;
  }
  public function getVendor(): string{
    return $this->vendor;
  }

  public function setName(string $name): Module{
    $name = trim($name);
    if(strlen($name) === 0){
      throw new InvalidArgumentException("Name is empty");
    }
    $this->name = $name;
    return $this;
  }
  public function getName(): string{
    return $this->name;
  }

  public function setDescription(string $desc): Module{
    $this->description = $desc;
    return $this;
  }
  public function getDescription(): string{
    return $this->description;
  }

  public function setPath(string $path): Module{
    $this->path = $path;
    return $this;
  }
  public function getPath(): string{
    return $this->path;
  }

  public function setInstallationDate(?\DateTime $installationDate=null): Module{
    if($installationDate === null){
      $installationDate = new \DateTime(
        'now', new \DateTimeZone("Europe/Berlin")
      );
    }
    invariant(
      $installationDate !== null, "Module::setInstallDate: installDate is null"
    );
    $this->installationDate = $installationDate;
    return $this;
  }
  public function getInstallationDate(): \DateTime{
    return $this->installationDate;
  }

  public function setRoutingInfo(DoctrineCollection<RoutingInfo> $info): Module{
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
    return $this;
  }
  public function setRoutingInfoArray(array<RoutingInfo> $info): Module{
    return $this->setRoutingInfo(new ArrayCollection($info));
  }
  public function addRoutingInfo(RoutingInfo $info){
    $this->routingInfo->add($info);
    return $this;
  }
  public function getRoutingInfo(): DoctrineCollection<RoutingInfo>{
    return $this->routingInfo;
  }
  public function getRoutingInfoArray(): array<mixed>{
    return $this->routingInfo->toArray();
  }

  public function setCreator(User $creator): Module{
    $this->creator = $creator;
    return $this;
  }
  public function getCreator(): User{
    return $this->creator;
  }
}
