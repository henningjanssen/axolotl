<?php

use axolotl\util\_;

class LoginView extends PageView{
  public function __construct(
    bool $failedLogin = false, string $presetUser = "", string $presetPW = ""
  ){
    parent::__construct(t("Login"));
    $this->content =
      <x:frag>
        <bootstrap:panel use="primary">
          <bootstrap:panel:heading>Login</bootstrap:panel:heading>
          <bootstrap:panel:body>
            <form
              action={strval(_::SETTINGS("system.base_uri"))."/login"} method="post">
              <fieldset class="form-group">
                <label for="__ax_nick">{t('Username or e-mail')}</label>
                <input type="text" class="form-control" name="username"
                  placeholder={t('Username or e-mail')} value={$presetUser}/>
              </fieldset>
              <fieldset class="form-group">
                <label for="__ax_pw">{t('Password')}</label>
                <input type="password" class="form-control" name="password"
                  placeholder={t('password')} value={$presetPW}/>
              </fieldset>
              <input type="submit" value="Login"/>
            </form>
          </bootstrap:panel:body>
        </bootstrap:panel>
      </x:frag>;
    if($failedLogin){
      $this->content->appendChild(
        <bootstrap:alert use="warning">
          {t('The provided e-mail-adress/username and password-combination does not
          match any existing user (Login failed).')}
        </bootstrap:alert>
      );
    }
    $this->content->appendChild(
      <bootstrap:alert use="info">
        {t('This site uses Cookies to store information on your computer.')}
      </bootstrap:alert>
    );
  }
}
