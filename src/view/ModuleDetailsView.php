<?php

namespace axolotl\view;

use axolotl\entities\Module;
use axolotl\util\_;

class ModuleDetailsView extends PageView{
  public function __construct(?Module $module){
    parent::__construct("moduledetails.html", "moduledetails.title", true);

    $routings = array();
		foreach($module->getRoutingInfo() as $ri){
      $routings[] = array(
        'uri' => $ri->getURI(),
        'methods' => $ri->getMethodString(),
        'handler' => $ri->getHandler()
      );
		}

    $user = $module->getCreator();
    $this->setVars(array(
      "module" => array(
        'name' => $module->getName(),
        'vendor' => $module->getVendor(),
        'description' => $module->getDescription(),
        'path' => $module->getPath(),
        'installdate' => $module->getInstallationDate()->format('d.m.Y H:i')
      ),
      "routings" => $routings,
      "user" => array(
        "username" => $user->getUsername(),
        "mail" => $user->getEmail(),
        "name" => $user->getFullName(),
        "note" => $user->getNote(),
        "registered" => $user->getRegistration()->format($dateFormat),
        "lastactivity" => $user->getLastActivity()->format($dateFormat)
      )
    ));
  }
}
