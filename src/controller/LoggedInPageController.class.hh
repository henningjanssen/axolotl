<?hh // strict

namespace axolotl\controller;

use axolotl\exceptions\NotLoggedInException;
use axolotl\util\Session;

abstract class LoggedInPageController extends PageController{
  public function __construct(array<string> $vars){
    if(!Session::loggedIn()){
      throw new NotLoggedInException();
    }
    parent::__construct($vars);
  }
}
