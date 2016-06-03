<?hh // strict

namespace axolotl\controller;

abstract class PageController{
  private array<string> $vars;
  public function __construct(array<string> $vars){
    $this->vars = $vars;
  }

  public function execute(){}
}
