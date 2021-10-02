<?php

namespace axolotl\control;

use Doctrine\DBAL\Exception\UniqueConstraintViolationException;

use axolotl\entities\User;
use axolotl\exceptions\InvalidArgumentException;
use axolotl\view\EditUserView;
use axolotl\view\RedirectView;
use axolotl\util\_;
use axolotl\util\Doctrine;
use axolotl\util\Session;

class EditUserControl extends LoggedInPageControl{
  public function execute(): void{
    $user = null;
    if($this->hasVar('id')){
      $user = User::get(intval($this->vars['id']));
    }
    if($this->httpMethod === 'GET'){
      (new EditUserView($user))->render();
      return;
    }

    if($user === null){
      $user = User::newInstance();
    }
    $alerts = [];
    try{
      $user->setUsername(strval(_::POST('username', $user->getUsername())))
        ->setEmail(strval(_::POST('mail', $user->getEmail())))
        ->setFullName(strval(_::POST('name', $user->getFullName())))
        ->setNote(strval(_::POST('note', $user->getNote())));
    }
    catch(InvalidArgumentException $ex){
      $alerts[] = 'edituser.alert.malformed';
    }

    $triedPw = false;
    if(strlen(_::POST('pw', '')) > 0){
      $triedPw = true;
      if(_::POST('pw') !== _::POST('pw-confirm')){
        $alerts[] = 'edituser.alert.pwmissmatch';
      }
      else{
        $user->setPassword(strval(_::POST('pw')), false);
      }
    }
    $em = Doctrine::getEntityManager();

    if(strlen($user->getPassword()) === 0 && !$triedPw){
      $alerts[] = 'edituser.alert.nopw';
    }
    else{
      try{
        $em->persist($user);
        $em->flush();
      }
      catch(UniqueConstraintViolationException $ex){
        $alerts[] = 'editor.alert.uniqueviolation';
      }
    }

    if($this->hasVar('id') || count($alerts) > 0){
      (new EditUserView($user, $alerts))->render();
      return;
    }
    (new RedirectView("/user/{$user->getID()}"))->render();
  }
}
