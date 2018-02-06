<?php

namespace \axolotl\view;

use axolotl\entities\Module;
use axolotl\util\_;

class InstallModuleView extends PageView{
  public function __construct(
    array $modules = array(), array $errors = array()
  ){
    parent::__construct("installmodule.title", true);

    $mods = array();
    foreach($momdules as $m){
      $mods[] = array(
        'link' => '/m/'.urlencode(strtolower($m->getVendor()))
          .'/'.urlencode(strtolower($m->getName())).'/',
        'name' => $m->getName()
      );
    }

    $this->setTemplateFile('installmodule.html');
    $this->setVars(array(
      'errors' => $errors,
      'installedmodules' => $mods
    ));
  }
}
