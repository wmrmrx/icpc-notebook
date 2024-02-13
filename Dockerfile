FROM rust:slim-bookworm

RUN apt-get update && \
    apt-get install -y wget xz-utils make && \
    wget https://github.com/typst/typst/releases/download/v0.10.0/typst-x86_64-unknown-linux-musl.tar.xz && \
    tar -xJf typst-x86_64-unknown-linux-musl.tar.xz && \
    mv typst-x86_64-unknown-linux-musl/typst /bin

WORKDIR /app

COPY . .

VOLUME /app/output

CMD ["make", "pdf"]
