FROM alpine:latest
LABEL maintainer="Emin Gadzhiev"
LABEL description="Dockerfile installs python."
RUN apk add python3 && mkdir docs
COPY README docs/README
EXPOSE 80/tcp
