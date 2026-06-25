###
# THIS FILE WAS GENERATED AUTOMATICALLY. DO NOT CHANGE IT.
###

ARG DOCKER_IMAGE_ROOT=ubuntu:24.04
FROM ${DOCKER_IMAGE_ROOT} AS base

ENV DEBIAN_FRONTEND noninteractive

RUN apt update --fix-missing && \
    apt -y install --no-install-recommends python3 python3-pip python3-venv\
    git build-essential pkg-config graphviz && \
    apt -y install sudo && \
    rm -rf /var/lib/apt/lists/* && \
    update-alternatives --install /usr/bin/python python /usr/bin/python3 1

FROM base AS cpp

RUN apt update --fix-missing && apt -y --no-install-recommends install cppcheck lib32z1 \
    make cmake clang clang-format clang-tidy doxygen libcmocka0 libcmocka-dev gdb screen wget curl && \
    rm -rf /var/lib/apt/lists/*

FROM cpp AS esp32
# esp-idf dependencies, https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html
RUN apt update --fix-missing && apt -y --no-install-recommends install \
    git wget flex bison gperf python3 python3-venv cmake ninja-build ccache \
    libffi-dev libssl-dev dfu-util libusb-1.0-0 \
    curl openocd && \
    rm -rf /var/lib/apt/lists/*

ARG ESPRESSIF_IDF_TAG="v5.5.1"
ARG ESPRESSIF_IDF_VERSION="${ESPRESSIF_IDF_TAG}"
ARG ESPRESSIF_IDF_PATH="/opt/esp-idf"
ARG ESPRESSIF_REQUIREMENTS_FILE_PATH="${ESPRESSIF_IDF_PATH}/tools/requirements/requirements.core.txt"
ARG ESPRESSIF_IDF_REPO_URL="https://github.com/espressif/esp-idf.git"
ARG ESPRESSIF_TOOLS_PATH="/root/.espressif"
ARG RUN_CLANG_TIDY_SCRIPT_URL="https://raw.githubusercontent.com/llvm/llvm-project/llvmorg-16.0.0/clang-tools-extra/clang-tidy/tool/run-clang-tidy.py"
ENV IDF_TOOLS_PATH ${ESPRESSIF_IDF_PATH}
ENV IDF_PATH ${ESPRESSIF_IDF_PATH}

WORKDIR /opt

RUN umask 0002 && git clone --single-branch --branch ${ESPRESSIF_IDF_VERSION} --recursive --depth=1 --shallow-submodules ${ESPRESSIF_IDF_REPO_URL} ${ESPRESSIF_IDF_PATH}
RUN test -f ${ESPRESSIF_REQUIREMENTS_FILE_PATH} && sed -i 's/click/click>=7.0,<8.2.0/g' ${ESPRESSIF_REQUIREMENTS_FILE_PATH}
RUN umask 0002 && ${ESPRESSIF_IDF_PATH}/install.sh
RUN umask 0002 && ${ESPRESSIF_IDF_PATH}/tools/idf_tools.py install esp-clang

ENV LC_ALL=C

RUN umask 0002 && mkdir /opt/esp/ && echo '#!/usr/bin/env bash\n\
\n\
set -e\n\
\n\
. $IDF_PATH/export.sh\n\
\n\
exec "$@"' >  /opt/esp/entrypoint.sh && chmod 775 /opt/esp/entrypoint.sh

RUN umask 0002 &&  curl -o /usr/bin/run-clang-tidy.py  ${RUN_CLANG_TIDY_SCRIPT_URL} && \
chmod 775 /usr/bin/run-clang-tidy.py

WORKDIR /opt

FROM esp32 AS custom_lora_pilot
# user can add his docker code below which will be integrated with
# main docker file and not overwritten by pwrforge update
FROM custom_lora_pilot AS lora_pilot_dev

ARG UID_NUMBER=1000
ARG GID_NUMBER=1000
ARG SSH_PORT=2000
ARG CONAN_LOGIN_USERNAME=""
ARG CONAN_PASSWORD=""
ARG DEV_USER=ubuntu

ENV CONAN_LOGIN_USERNAME=${CONAN_LOGIN_USERNAME}
ENV CONAN_PASSWORD=${CONAN_PASSWORD}

WORKDIR /opt

# configure ssh
RUN apt update --fix-missing && apt install -y --no-install-recommends openssh-server && \
    rm -rf /var/lib/apt/lists/* && \
    ssh-keygen -A && mkdir -p /run/sshd && \
    echo "Port $SSH_PORT" >> /etc/ssh/sshd_config

EXPOSE $SSH_PORT

RUN printf "\n\nCONFIGURING USER $DEV_USER - DEV ENV ONLY!\n\n" >&2 && \
    apt -y install sudo && \
    if ! getent group "$GID_NUMBER" >/dev/null; then \
        if getent group "$DEV_USER" >/dev/null; then \
            groupmod -g "$GID_NUMBER" "$DEV_USER"; \
        else \
            groupadd -g "$GID_NUMBER" "$DEV_USER"; \
        fi; \
    fi && \
    if ! id -u "$DEV_USER" >/dev/null 2>&1; then \
        useradd -m -s /bin/bash -N -o -u "$UID_NUMBER" -g "$GID_NUMBER" "$DEV_USER"; \
    else \
        usermod -o -u "$UID_NUMBER" -g "$GID_NUMBER" "$DEV_USER"; \
    fi && \
    mkdir -p /etc/sudoers.d && \
    echo "$DEV_USER ALL=(ALL) NOPASSWD:ALL" > "/etc/sudoers.d/90-$DEV_USER" && \
    chmod 0440 "/etc/sudoers.d/90-$DEV_USER" && \
    passwd -d "$DEV_USER" || true
RUN if ! getent group "4" >/dev/null; then \
        groupadd -g "4" "hostgrp_4"; \
    fi
RUN if ! getent group "20" >/dev/null; then \
        groupadd -g "20" "hostgrp_20"; \
    fi
RUN if ! getent group "24" >/dev/null; then \
        groupadd -g "24" "hostgrp_24"; \
    fi
RUN if ! getent group "25" >/dev/null; then \
        groupadd -g "25" "hostgrp_25"; \
    fi
RUN if ! getent group "27" >/dev/null; then \
        groupadd -g "27" "hostgrp_27"; \
    fi
RUN if ! getent group "29" >/dev/null; then \
        groupadd -g "29" "hostgrp_29"; \
    fi
RUN if ! getent group "30" >/dev/null; then \
        groupadd -g "30" "hostgrp_30"; \
    fi
RUN if ! getent group "44" >/dev/null; then \
        groupadd -g "44" "hostgrp_44"; \
    fi
RUN if ! getent group "46" >/dev/null; then \
        groupadd -g "46" "hostgrp_46"; \
    fi
RUN if ! getent group "100" >/dev/null; then \
        groupadd -g "100" "hostgrp_100"; \
    fi
RUN if ! getent group "114" >/dev/null; then \
        groupadd -g "114" "hostgrp_114"; \
    fi
RUN if ! getent group "124" >/dev/null; then \
        groupadd -g "124" "hostgrp_124"; \
    fi
RUN if ! getent group "984" >/dev/null; then \
        groupadd -g "984" "hostgrp_984"; \
    fi

COPY requirements.txt requirements.txt
RUN python3 -m venv /opt/venv && \
    /opt/venv/bin/pip install --upgrade pip && \
    /opt/venv/bin/pip install -r requirements.txt && \
    rm requirements.txt
ENV PATH="/opt/venv/bin:${PATH}"

COPY pwrforge-*-py3-none-any.whl /opt/pwrforge-0-py3-none-any.whl
RUN /opt/venv/bin/pip install /opt/pwrforge-0-py3-none-any.whl

RUN usermod -a -G dialout ${DEV_USER}
ENV HOME=/home/${DEV_USER}
USER ${DEV_USER}
RUN /bin/bash -c "echo 'source $IDF_PATH/export.sh'" >> ~/.bashrc
CMD ["/bin/bash"]
WORKDIR /workspace