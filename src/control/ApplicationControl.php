<?php

namespace axolotl\control;

use axolotl\entities\Module;
use axolotl\exceptions\NotLoggedInException;
use axolotl\util\_;
use axolotl\util\Doctrine;
use axolotl\util\Session;
use axolotl\view\RedirectView;

class ApplicationControl{
  public function __construct(string $uri, string $httpMethod){
    $this->uri = $uri;
    $this->httpMethod = $httpMethod;
  }

  public function execute(): void{
    $dispatcher = \FastRoute\simpleDispatcher(
      function(\FastRoute\RouteCollector $r){
        $r->addRoute('GET', '[/[home]]', HomePageControl::class);
        $r->addRoute(['GET','POST'], '/login', LoginControl::class);
        $r->addRoute('GET', '/logout', LogoutControl::class);
        $r->addRoute(['GET'], '/settings/modules', ModuleControl::class);
        $r->addRoute(['GET', 'POST'],
          '/settings/modules/install', InstallModuleControl::class
        );
        $r->addRoute('GET',
          '/settings/modules/details/{vendor}/{module}[/]',
          ModuleDetailsControl::class
        );
        $r->addRoute('GET',
          '/settings/modules/uninstall/{vendor}/{module}[/]',
          RemoveModuleControl::class
        );
        $r->addRoute(['GET', 'POST'],
          '/api/upload/{name:.+}', UploadControl::class
        );
        $r->addRoute('GET',
          '/static/m/{vendor:.+}/{module:.+}/{path:.+}',
          StaticContentControl::class
        );
        $r->addRoute('GET', '/static/{path:.+}', StaticContentControl::class);
        $r->addRoute('GET', '/error/{errno:\d+}', ErrorControl::class);
        //$r->addRoute(['GET','POST'], '/user/edit/{id:\d+}', 'somehandler');
        //$r->addRoute('GET', '/user/list', 'somehandler');
        //$r->addRoute('GET', '/user/new', 'somehandler');
        //$r->addRoute('GET', '/user/show/{id:\d+}', 'somehandler');
        $r->addRoute('GET', '/about', AboutControl::class);
        $r->addRoute('GET', '/i18n/{ns}/{lang}[/]', LocalesControl::class);

        // Add routings for modules
        $modules = Doctrine::getEntityManager()
          ->getRepository(Module::class)
          ->findAll();
        foreach($modules as $mod){
          foreach($mod->getRoutingInfo() as $i){
            $r->addRoute(
              $i->getMethods(),
              '/m/'.urlencode($mod->getVendor())
                .'/'.urlencode($mod->getName()).$i->getURI(),
              $i->getHandler()
            );
          }
        }
      }
    );

    $pos = strpos($this->uri, '?');
    if($pos !== false){
      $this->uri = substr($this->uri, 0, $pos);
    }
    $pos = strpos($this->uri, _::SETTINGS("system.base_uri"));
    if($pos === 0){
      $this->uri = substr($this->uri, strlen(_::SETTINGS("system.base_uri")));
    }
    if($this->uri[0] !== '/'){
      $this->uri = "/$this->uri";
    }
    $this->uri = rawurldecode($this->uri);

    $this->initIntl();

    $routeInfo = $dispatcher->dispatch($this->httpMethod, $this->uri);
    switch($routeInfo[0]){
      case \FastRoute\Dispatcher::NOT_FOUND:
        (new RedirectView("/error/404"))->render();
      break;

      case \FastRoute\Dispatcher::METHOD_NOT_ALLOWED:
        //405 Method not allowed
        (new RedirectView("/error/405"))->render();
      break;

      case \FastRoute\Dispatcher::FOUND:
        $handler = $routeInfo[1];
        $vars = $routeInfo[2];
        try{
          (new $handler($vars, $this->httpMethod))->execute();
        }
        catch(NotLoggedInException $nliex){
          (new LoginControl($vars, $this->httpMethod, $this->uri))->execute();
        }
      break;
    }
  }

  private function initIntl(): void {
    $defaultDomain = 'en';
    try {
      $user = Session::getCurrentUser();
      $domain = $user->getLanguage() ?? $defaultDomain;
    } catch (NotLoggedInException $e) {
      $domain = $defaultDomain;
    }
  }
}
