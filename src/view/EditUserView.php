<?php

namespace axolotl\view;

use axolotl\entities\User;

class EditUserView extends PageView{
  public function __construct(?User $user, array $alerts = []){
    parent::__construct(
      "edituser.html",
      ($user && $user->getID() > 0)
        ?"i18n:edituser.title"
        :'i18n:edituser.title_new'
    );
    $this->setVars(array(
      "alerts" => $alerts,
      "user" => $user
    ));
  }
}
