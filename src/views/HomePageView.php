<?php

namespace \axolotl\view;

use axolotl\entities\Module;
use axolotl\entities\User;

class HomePageView extends PageView{
  public function __construct(
    User $user, array $modules
  ){
    parent::__construct("home.title");
    $dateFormat = "d.m.Y H:i";
    $this->setTemplateFile();
    $this->setVars(array(
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
