<?php

namespace axolotl\view;

use axolotl\entities\Module;
use axolotl\entities\User;

class ListUsersView extends PageView{
  public function __construct(
    array $users, int $ownID
  ){
    parent::__construct("listusers.html", "i18n:listusers.title");
    $dateFormat = "d.m.Y H:i";
    $this->setVars(array(
      "users" => $users,
      "ownID" => $ownID
    ));
  }
}
