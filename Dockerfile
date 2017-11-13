FROM webdevops/apache:debian-8

# System-stuff
USER root
RUN addgroup application --gid 1000 && adduser application --disabled-password --gecos "" --uid 1000 --gid 1000
RUN mkdir /system-data
ENV APACHE_WEBMASTER webmaster@localhost
ENV APACHE_AXL_SUBDOMAIN /axl/

# install hhvm
RUN apt-key adv --recv-keys --keyserver hkp://keyserver.ubuntu.com:80 0x5a16e7281be7a449\
  && echo deb http://dl.hhvm.com/debian jessie main | tee /etc/apt/sources.list.d/hhvm.list
RUN apt-get -qq update && apt-get -y -qq install hhvm-dbg git && update-rc.d hhvm defaults
RUN touch /system-data/hhvm.log && chmod 666 /system-data/hhvm.log

# install postgresql
RUN apt-get -y -qq install postgresql postgresql-common postgresql-client
RUN echo "host all  all    0.0.0.0/0  md5" >> /etc/postgresql/9.4/main/pg_hba.conf
RUN echo "listen_addresses='*'" >> /etc/postgresql/9.4/main/postgresql.conf
RUN rm -rf /var/lib/postgresql/data && ln -s /system-data/postgresql /var/lib/postgresql/data
USER postgres
RUN /etc/init.d/postgresql start\
  && psql -c "create user axl with login password 'axlpw42' createdb;"\
  && psql -c "create database axolotl with owner axl encoding 'UTF8' template template0;"\
  && /etc/init.d/postgresql stop

USER root
RUN mkdir /letsencrypt
RUN openssl req -x509 -newkey rsa:4096 -keyout /system-data/cert-key.pem -out /system-data/cert.pem -nodes -days 365 -subj "/C=/ST=/L=/O=/OU=/CN=localhost"
COPY ./docker/* /system-data/
RUN rm /opt/docker/etc/httpd/vhost.conf && ln -s /system-data/apache-vhost.conf /opt/docker/etc/httpd/vhost.conf
RUN chmod +x /system-data/entrypoint.sh

RUN ln -s /system-data/supervisor-services.conf /opt/docker/etc/supervisor.d/services.conf

# Copy source and install dependencies
RUN mkdir /axl
WORKDIR /axl
COPY . /axl
RUN chmod +x ./getcomposer.sh && ./getcomposer.sh
RUN chown 1000:1000 /axl -R
USER application
RUN hhvm ./composer.phar config --global --auth github-oauth.github.com efcc64ce5081ce9c76c0c9bdd760ad90b2d6170c
RUN hhvm ./composer.phar update && hhvm ./vendor/bin/hh-autoload

# Create database
WORKDIR /axl/install
RUN chmod +x doctrine.sh
USER postgres
RUN /etc/init.d/postgresql start\
  && psql -daxolotl -f ./install.sql\
  && psql -daxolotl -c "alter database axolotl owner to axl;;"\
  && psql -daxolotl -c "alter table modules owner to axl;"\
  && psql -daxolotl -c "alter table routinginfo owner to axl;"\
  && psql -daxolotl -c "alter table users owner to axl;"\
  && psql -daxolotl -c "alter sequence modules_id_seq owner to axl;"\
  && psql -daxolotl -c "alter sequence routinginfo_id_seq owner to axl;"\
  && psql -daxolotl -c "alter sequence users_id_seq owner to axl;"\
  && hhvm ./create-admin.hh\
  && /etc/init.d/postgresql stop

# Clean up
WORKDIR /system-data
USER root
RUN rm /axl/install -rf
RUN rm /axl/docker -rf
RUN apt-get clean


#VOLUME ["/system-data/apache-vhost.conf", "/system-data/postgresql/", "/axl/", "/axl/modules/", "/app/"]
VOLUME ["/system-data/postgresql/", "/axl/", "/axl/modules/", "/app/", "/letsencrypt"]

# Setup
CMD ["/system-data/entrypoint.sh"]
