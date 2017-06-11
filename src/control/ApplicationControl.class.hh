<?hh // partial

namespace axolotl\control;

use axolotl\entities\Module;
use axolotl\exceptions\NotLoggedInException;
use axolotl\util\_;
use \RedirectView;

class ApplicationControl{
  public function __construct(private string $uri, private string $httpMethod){}

  public function execute(): void{
    $dispatcher = \FastRoute\simpleDispatcher(
      function(\FastRoute\RouteCollector $r){
        $ns = "\\axolotl\\control";
        $r->addRoute('GET', '[/[home]]',"$ns\\HomePageControl");
        $r->addRoute(['GET','POST'], '/login', "$ns\\LoginControl");
        $r->addRoute('GET', '/logout', "$ns\\LogoutControl");
        $r->addRoute(['GET'], '/settings/modules', "$ns\\ModuleControl");
        $r->addRoute(['GET', 'POST'],
          '/settings/modules/install', "$ns\\InstallModuleControl"
        );
        $r->addRoute('GET',
          '/settings/modules/details/{vendor}/{module}[/]',
          "$ns\\ModuleDetailsControl"
        );
        $r->addRoute('GET',
          '/settings/modules/uninstall/{vendor}/{module}[/]',
          "$ns\\RemoveModuleControl"
        );
        $r->addRoute(['GET', 'POST'],
          '/api/upload/{name:.+}', "$ns\\UploadControl"
        );
        $r->addRoute('GET',
          '/static/m/{vendor:.+}/{module:.+}/{path:.+}',
          "$ns\\StaticContentControl"
        );
        $r->addRoute('GET', '/static/{path:.+}', "$ns\\StaticContentControl");
        $r->addRoute('GET', '/error/{errno:\d+}', "$ns\\ErrorControl");
        //$r->addRoute(['GET','POST'], '/user/edit/{id:\d+}', 'somehandler');
        //$r->addRoute('GET', '/user/list', 'somehandler');
        //$r->addRoute('GET', '/user/new', 'somehandler');
        //$r->addRoute('GET', '/user/show/{id:\d+}', 'somehandler');
        $r->addRoute('GET', '/about', "$ns\\AboutControl");

        // Add routings for modules
        $modules = \axolotl\util\Doctrine::getEntityManager()
          ->getRepository(Module::class)
          ->findAll();
        foreach($modules as $mod){
          foreach($mod->getRoutingInfo() as $i)
          $r->addRoute(
            $i->getMethodString(),
            '/m/'.urlencode($mod->getVendor())
              .'/'.urlencode($mod->getName()).$i->getURI(),
            $i->getHandler()
          );
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
          (new $handler($vars))->execute();
        }
        catch(NotLoggedInException $nliex){
          (new LoginControl($vars, $this->uri))->execute();
        }
      break;
    }
  }
}
