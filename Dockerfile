FROM docker:stable

RUN apk add git openssh curl

RUN mkdir ~/.ssh && \
chmod 700 ~/.ssh && \
ssh-keyscan -t rsa gitlab.com > ~/.ssh/known_hosts && \
ssh-keyscan -t rsa 35.231.145.151 >> ~/.ssh/known_hosts

COPY setup-ssh-key.sh setup-ssh-key.sh