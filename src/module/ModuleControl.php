<?php

namespace axolotl\module;

use \Doctrine\ORM\Tools\SchemaTool;

use axolotl\util\Doctrine;

abstract class ModuleControl{
  public function install(): bool{
    $schemaTool = $this->getSchemaTool();
    $classes = $this->getClasses();
    $schemaTool->createSchema($classes);
    return true;
	}

  public function uninstall(): bool{
    $schemaTool = $this->getSchemaTool();
    $classes = $this->getClasses();
    $schemaTool->dropSchema($classes);
    return true;
	}

  public function update(): bool{
    $schemaTool = $this->getSchemaTool();
    $classes = $this->getClasses();
    $schemaTool->updateSchema($classes, true);
    return true;
	}

  public function getSchemaTool(): SchemaTool{
    $em = Doctrine::getEntityManager();
    return new SchemaTool($em);
  }

  public function backup(): void{}
  public abstract function getRoutings(): array;
  public abstract function getClasses(): array;
}
