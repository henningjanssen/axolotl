<?hh // strict

use axolotl\util\_;

class LoginView extends PageView{
  public function __construct(
    bool $failedLogin = false, string $presetUser = "", string $presetPW = ""
  ){
    parent::__construct("Login");
    $this->content =
      <x:frag>
        <bootstrap:panel use="primary">
          <bootstrap:panel:heading>Login</bootstrap:panel:heading>
          <bootstrap:panel:body>
            <form
              action={strval(_::SETTINGS("axolotl.base_uri"))."login"} method="post">
              <fieldset class="form-group">
                <label for="__ax_nick">Username or E-Mail</label>
                <input type="text" class="form-control" name="__ax_nick"
                  placeholder="Username or e-mail" value={$presetUser}/>
                <input type="hidden" class="form-control" name="__ax_login"
                  value="1"/>
              </fieldset>
              <fieldset class="form-group">
                <label for="__ax_pw">Password</label>
                <input type="password" class="form-control" name="__ax_pw"
                  placeholder="password" value={$presetPW}/>
              </fieldset>
              <input type="submit" value="Login"/>
            </form>
          </bootstrap:panel:body>
        </bootstrap:panel>
      </x:frag>;
    if($failedLogin){
      $this->content->appendChild(
        <bootstrap:alert use="warning">
          The provided e-mail-adress/username and password-combination does not
          match any user in the database (Login failed).
        </bootstrap:alert>
      );
    }
    $this->content->appendChild(
      <bootstrap:alert use="info">
        This site uses Cookies to store information on your computer.
      </bootstrap:alert>
    );
  }
}
