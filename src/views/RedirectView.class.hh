<?hh // strict

use axolotl\util\_;

class RedirectView extends PageView{
  public function __construct(string $target){
    parent::__construct("Redirecting");
    $base = strval(_::SETTINGS("axolotl_base_uri"));
    $this->setHTTPStatusCode(307);
    $this->setHeader("Location: $base$target");
  }
}
