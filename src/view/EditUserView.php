<?php

namespace axolotl\view;

use axolotl\entities\User;

class EditUserView extends PageView{
  public function __construct(?User $user, array $alerts = []){
    parent::__construct(
      "edituser.html",
      ($user && $user->getID() > 0) ?"edituser.title" :'edituser.title_new',
      true
    );
    $this->setVars(array(
      "alerts" => $alerts,
      "user" => $user
    ));
  }
}
