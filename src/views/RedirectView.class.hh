<?hh // strict

use axolotl\util\_;

class RedirectView extends PageView{
  public function __construct(string $target){
    parent::__construct("Redirecting | axolotl");
    $base = strval(_::SETTINGS("axolotl_base_uri"));
    if($base[strlen($base)-1] !== '/'){
      $base .= '/';
    }
    $this->setHTTPStatusCode(307);
    $this->setHeader("Location: $base$target");
  }
}
