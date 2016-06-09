<?hh // strict

namespace axolotl\controller;

use axolotl\util\Session;

abstract class LoggedInPageController extends PageController{
  public function __construct(array<string> $vars){
    if(!Session::loggedIn()){
      throw new NotLoggedInException();
    }
    parent::construct($vars);
  }
}
