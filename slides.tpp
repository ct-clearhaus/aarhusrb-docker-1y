--## Show slides: tpp slides.tpp

--author Casper Thomsen
--title AWS og docker
--center Lessons Learned after one year in production

--date 2015-12-07


--newpage lessons-learned
--heading Lessons learned

1. AWS is maturing
---

2. We're getting better at using AWS
---

3. Docker is maturing
---

4. We're getting better at using Docker


--newpage how-we-do
--heading How we do AWS and Docker

* Github repos (74)

* CircleCI builds docker images

* Build AMI: packer.io, git, AWS plumbing

* Update CF and kick instances

* On boot:
  1. Ramdisk w. credentials from S3
  2. `docker-compose up`
  3. Launch rsyslog and ossec

--newpage infrastructure
--heading Infrastructure

* Hand drawing ...

--newpage aws-maturing
--heading AWS is maturing (1)

* Cloud formation
  - VPN connection & static routing(?)
  - multiple EIPs to one ANI(?)
  - public RDS(?)
  - non-deletable stack(?)
  - infinity update loop(?)
  + update in parallel
  - non-updateable stack
  - renaming resources
  - duplicate (in|e)gress rules (and names)

--newpage aws-maturing
--heading AWS is maturing (2)

* Droplets of improvements

* RDS
  - logging
  - password

--newpage aws-usage
--heading Using AWS better (1)

* Network: separation, scaling, duties

* Firewalling: glue SGs together, debug

* ELB: multi-AZ, cross-AZ

* Separate MPI from GW

* On boot: grab EIP, update DNS

* Janitor work: S3VpcEndpoint, renaming, SshKey, connection draining, ...

--newpage aws-usage
--heading Using AWS better (2)

* Tighten egress firewalling: "dependencies to S3"

* Deploying

* Split GW into multiple CF stacks

* Auto-scaling *automatically*

* Handling secrets



--newpage docker-maturing
--heading Docker is maturing

* Logging: --log-driver

* Orchestration: fig -> compose

* Registry v2

* Image security (notary)


--newpage using-docker
--heading Using Docker (1)

* repo.git/build
  |-- build.sh
  |-- Dockerfile
  `-- start.sh

* Orchestrated with docker-compose

--newpage using-docker
--heading Using Docker (2)

* Security:
  - Read-only containers
  - Drop capabilities
  - Drop privileges
  - No ICC except linked containers

* Secrets mounted from host

* Logging via syslog log-driver

--newpage using-docker
--heading Using Docker better?

* Network

* Notary

* Use runC instead

* AWS ECS for non-PCI stuff


--newpage aims
--heading Aims (1)

* Automate, automate, automate

* Resilience (uptime, warmth)

* Separate procesr (security, scaling)

* Minimize Gem usage (security, warmth)

* Logging

--newpage aims
--heading Aims (2)

* Improve CI/CD (happiness)
  - smoother deployments
  - syntax check
  - code analysis

* Business stuff (suez, void, credit, mpi v2)


--newpage questions

--center   ____                  _   _                ___  
--center  / __ \                | | (_)              |__ \ 
--center | |  | |_   _  ___  ___| |_ _  ___  _ __  ___  ) |
--center | |  | | | | |/ _ \/ __| __| |/ _ \| '_ \/ __|/ / 
--center | |__| | |_| |  __/\__ \ |_| | (_) | | | \__ \_|  
--center  \___\_\\__,_|\___||___/\__|_|\___/|_| |_|___(_)  


--newpage More on secrets

* Secrets:
  - Bake in: no.
  - Mount in:
    * from volume-only container
    * from host
  - Key-value store:
    * etcd (github.com/coreos/etc, github.com/xordataexchange/crypt)
    * vault (by hashicorp)
    * keywhiz (github.com/square/keywhiz)
