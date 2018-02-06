<?php

namespace axolotl\control;

use axolotl\view\RedirectView;
use axolotl\util\Session;

class LogoutControl extends PageControl{
  public function execute(): void{
    Session::logout();
    (new RedirectView("/login"))->render();
  }
}
