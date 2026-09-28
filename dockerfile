FROM ubuntu:latest

RUN apt-get update && apt-get install -y g++ make gdb valdrind && rm -f /var/lib/apt/lists/*

WORKDIR /campusGuardApp

COPY . .

RUN make

CMD ["./campusguard"]