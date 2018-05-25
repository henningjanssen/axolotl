<?php

namespace axolotl\control;

use axolotl\entities\User;
use axolotl\view\ListUsersView;
use axolotl\view\RedirectView;
use axolotl\util\_;
use axolotl\util\Doctrine;
use axolotl\util\Session;

class ListUsersControl extends LoggedInPageControl{
  public function execute(): void{
    if(_::GET('delete', -1) > 0){
      $del = User::get(intval(_::GET('delete')));
      if($del){
        $em = Doctrine::getEntityManager();
        $em->remove($del);
        $em->flush();
      }
      (new RedirectView('/users'))->render();
      return;
    }

    $users = User::getAll();
    $ownID = Session::getCurrentUserID();
    (new ListUsersView($users, $ownID))->render();
  }
}
