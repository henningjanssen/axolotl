<?php

namespace axolotl\control;

use \ModuleDetailsView;
use axolotl\entities\Module;

class ModuleDetailsControl extends LoggedInPageControl{
  public function execute(): void{
    $module = Module::getByName(
			strval($this->vars['vendor']),
			strval($this->vars['module'])
		);
		(new ModuleDetailsView($module))->render();
  }
}
