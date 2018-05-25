<?php

namespace axolotl\control;

use axolotl\entities\User;
use axolotl\view\ListUsersView;
use axolotl\util\_;
use axolotl\util\Doctrine;
use axolotl\util\Session;

class ListUsersControl extends LoggedInPageControl{
  public function execute(): void{
    if(_::POST('delete') !== null){
      $del = User::get(intval(_::POST('delete')));
      if($del){
        $em = Doctrine::getEntityManager();
        $em->remove($del);
        $em->flush();
      }
    }

    $users = User::getAll();
    $ownID = Session::getCurrentUserID();
    (new ListUsersView($users, $ownID))->render();
  }
}
