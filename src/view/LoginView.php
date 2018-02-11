<?php

namespace axolotl\view;

use axolotl\util\_;

class LoginView extends PageView{
  public function __construct(
    bool $failedLogin = false, string $presetUser = "", string $presetPW = ""
  ){
    parent::__construct("login.html", "login.title", true);
    $this->setVars(array(
      'user' => $presetUser,
      'pw' => $presetPW,
      'failedlogin' => $failedLogin
    ));
  }
}
