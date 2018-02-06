<?php

namespace axolotl\control;

use axolotl\view\ErrorView;

class ErrorControl extends PageControl{
  public function execute(): void{
    (new ErrorView(intval($this->vars["errno"])))->render();
  }
}
