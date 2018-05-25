<?php

namespace axolotl\entities;

use \axolotl\exceptions\EntityNotFoundException;
use \axolotl\exceptions\InvalidArgumentException;
use \axolotl\util\Doctrine;
use \axolotl\util\Log;
use \Doctrine\Common\Collections\ArrayCollection;
use \Doctrine\Common\Collections\Collection as DoctrineCollection;
use \Doctrine\ORM\Mapping\UniqueConstraint;

/**
 * @Entity
 * @Table(name="modules", uniqueConstraints={
 *  @UniqueConstraint(name="mod_id", columns={"vendor", "name"})
 * })
 */
class Module{
  /** @Id @Column(type="integer") @GeneratedValue */
  protected $id;

  /** @Column(type="text") */
  protected $vendor;

  /** @Column(type="text") */
  protected $name;

  /** @Column(type="text") */
  protected $description;

  /** @Column(type="text") */
  protected $path;

  /**
   * @OneToMany(
   *  targetEntity="RoutingInfo",
   *  mappedBy="module",
   *  cascade={"persist", "remove"},
   *  orphanRemoval=true
   * )
   */
  protected $routingInfo;

  /** @Column(type="datetimetz", name="installed_at") */
  protected $installationDate;

  /** @ManyToOne(targetEntity="User", inversedBy="installedModules") */
  protected $creator;

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

  public static function getByName(string $vendor, string $name): Module{
		$entityManager = Doctrine::getEntityManager();
    $qb = $entityManager->createQueryBuilder();
		$query = $qb->select('m')
			->from(Module::class, 'm')
			->where(
				$qb->expr()->andX(
					$qb->expr()->eq('m.vendor', ':vendor'),
					$qb->expr()->eq('m.name', ':name')
				)
			)
			->setParameter('vendor', $vendor)
			->setParameter('name', $name)
			->getQuery();
		try{
			$module = $query->getSingleResult();
      return $module;
		}
		catch(\Doctrine\ORM\NoResultException $nrex){
			Log::error('Module::getByName',
				"Module not found. Query: `{$query->getSQL()}`"
				.", vendor: `{$vendor}`"
				.", module: `{$name}`"
			);
      throw new EntityNotFoundException("Module {$vendor}/{$name} not found");
		}
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
    $this->installationDate = $installationDate;
    return $this;
  }
  public function getInstallationDate(): \DateTime{
    return $this->installationDate;
  }

  public function setRoutingInfo(DoctrineCollection $info): Module{
    $em = Doctrine::getEntityManager();
    foreach($this->routingInfo as $ri){
      $ri->setModule(null);
      $em->remove($ri);
    }
    $hasRoot = false;
    foreach($info as $i){
      if($i->getURI() === '/'){
        $hasRoot = true;
      }
      $i->setModule($this);
    }
    if(!$hasRoot){
      throw new InvalidArgumentException('Module does not provide root');
    }
    $this->routingInfo = $info;
    return $this;
  }
  public function setRoutingInfoArray(array $info): Module{
    return $this->setRoutingInfo(new ArrayCollection($info));
  }
  public function addRoutingInfo(RoutingInfo $info): Module{
    $info->setModule($this);
    $this->routingInfo->add($info);
    return $this;
  }
  public function getRoutingInfo(): DoctrineCollection{
    return $this->routingInfo;
  }
  public function getRoutingInfoArray(): array{
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
