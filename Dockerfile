FROM php:7.0-apache

# System-stuff
RUN apt-get update && apt-get install -y git libzip-dev && apt-get clean
RUN pecl install zip
RUN mkdir /system-data
ENV APACHE_WEBMASTER webmaster@localhost
ENV APACHE_AXL_SUBDOMAIN /axl/

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
RUN php ./composer.phar config --global --auth github-oauth.github.com efcc64ce5081ce9c76c0c9bdd760ad90b2d6170c
RUN php ./composer.phar update

# Create database
WORKDIR /axl/install

# Clean up
WORKDIR /system-data
RUN rm /axl/install -rf
RUN rm /axl/docker -rf
RUN apt-get clean

VOLUME ["/axl/modules/", "/app/", "/letsencrypt"]

# Setup
CMD ["/system-data/entrypoint.sh"]
