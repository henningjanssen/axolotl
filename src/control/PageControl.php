<?php

namespace axolotl\control;

abstract class PageControl{
  protected $vars;
  public function __construct(array $vars, string $httpMethod){
    $this->vars = $vars;
    $this->httpMethod = $httpMethod;
  }

  final public function hasVar(string $name){
    return array_key_exists($name, $this->vars);
  }

  public abstract function execute(): void;
}
