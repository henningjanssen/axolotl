<?php

namespace axolotl\view;

use axolotl\entities\Module;
use axolotl\util\_;

class ModuleView extends PageView{
  public function __construct(
    array $modules
  ){
    parent::__construct("module.html", "module.title", true);
  }
}
