<?hh // strict


class LoginView extends PageView{
  public function __construct(
    bool $failedLogin = false, string $presetUser = "", string $presetPW = ""
  ){
    parent::__construct("Login | axolotl");
    $this->content = <bootstrap:panel use="primary">
        <bootstrap:panel:heading>Login</bootstrap:panel:heading>
        <bootstrap:panel:body>
          <form>
            <fieldset class="form-group">
              <label for="__ax_nick">Username or E-Mail</label>
              <input type="text" class="form-control" name="__ax_nick"
                placeholder="Username or e-mail" value="{$presetUser}"/>
              <input type="hidden" class="form-control" name="__ax_login"
                value="1"/>
            </fieldset>
            <fieldset class="form-group">
              <label for="__ax_pw">Password</label>
              <input type="password" class="form-control" name="__ax_login"
                placeholder="password" value="{$presetPW}"/>
            </fieldset>
          </form>
        </bootstrap:panel:body>
      </bootstrap:panel>;
  }
}
