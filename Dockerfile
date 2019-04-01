FROM ubuntu:bionic

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && \
    apt-get install -y python \
                    python-pip \
                    git \
                    curl \
                    vim \
                    doxygen \
                    jq && \
    apt-get autoremove && \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Install required python modules
COPY requirements.txt /tmp
RUN pip install -r /tmp/requirements.txt
