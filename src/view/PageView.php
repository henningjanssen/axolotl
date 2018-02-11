<?php

namespace axolotl\view;

use axolotl\util\_;
use axolotl\util\AXLSettingsFile;
use axolotl\util\Doctrine;
use axolotl\util\Session;

abstract class PageView extends View{
  protected $baseuri;
  protected $modulelist = array();
  protected $modulenav = array();
  protected $templateAdditionalPath = array();
  protected $templateFile;
  protected $title = "";
  protected $i18nTitle = false;
  protected $vars = array();

  public function __construct(string $title = "", bool $i18nTitle = false){
    $this->baseuri = strval(_::SETTINGS("system.base_uri", ""));
    $this->tempalteDir = realpath(__DIR__.'/../../templates');

    $this->setTitle($title, $i18nTitle);

    if(Session::loggedIn()){
      $em = Doctrine::getEntityManager();
      $modules = $em
        ->getRepository(\axolotl\entities\Module::class)
        ->findBy(array(), array('name' => 'ASC', 'vendor' => 'ASC'));
      foreach($modules as $m){
        $this->modulelist[] = array(
          'link' => "m/{$m->getVendor()}/{$m->getName()}/",
          'name' => $m->getName()
        );
      }
    }
  }

  final protected function addTemplateDirectory(string $ns, string $dir){
    $this->$templateAdditionalPath[$ns] = $dir;
  }

  final protected function setModuleNavigation(array $navs): void{
    if(count($navs) === 0){
      $this->modulesnav = array();
      return;
    }
    $this->modulenav = array();
    foreach($navs as $name => $url){
      $this->modulenav[] = array(
        'link' => $url,
        'name' => $name
      );
    }
  }

  final protected function setTemplateFile(string $file): void{
    if(strlen($dir) === 0){
      return;
    }
    $this->templateFile = $file;
  }

  final protected function setTitle(string $title, bool $i18n = false): void{
    $this->title = array(
      'i18n' => strlen($title) > 0 ? $i18n : false,
      'value' => $title
    );
  }

  final protected function setVars(array $vars): void{
    $this->vars = $vars;
  }

  final public function render(): void{
    $templvars = array(
      'baseuri' => $this->baseuri,
      'loggedin' => Session::loggedIn(),
      'modulelist' => $this->modulelist,
      'modulenav' => $this->modulenav,
      'title' => $this->title,
      'upload' => array(
        'chunkSize' => _::SETTINGS('upload.chunksize', 1*1024*1024),
        'simul' => _::SETTINGS('upload.simul', 3)
      )
    );
    $templvars = array_merge(
      $templvars,
      $this->vars
    );

    $twigLoader = new \Twig_Loader_Filesystem(
      realpath(__DIR__.'/../../templates/')
    );
    foreach($this->$templateAdditionalPath as $ns => $p){
      $twigLoader->addPath($p, $ns);
    }
    $twig = new \Twig_Environment($loader, array(
      'cache' => __DIR__.'/../../cache/twig/'.$this->templateDir
    ));
    $template = $twig->load($this->templateFile);
    print($template->render($vars));
  }
}
