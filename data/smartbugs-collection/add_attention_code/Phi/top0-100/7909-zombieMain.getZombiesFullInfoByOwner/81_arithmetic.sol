 

 
 pragma solidity ^0.4.10;
 
 contract TimeLock {

     mapping(address => uint) public balances;
     mapping(address => uint) public lockTime;


  using SafeMath for uint256;

  struct Zombie {
    bytes32 dna;
    uint8 star;
    uint16 roletype;
    bool isFreeZombie;
  }

  Zombie[] public zombies;
  mapping (uint => address) public zombieToOwner;
  mapping (address => uint) ownerZombieCount;

  function getZombiesFullInfoByOwner(address _owner) external view returns(uint[] id,bytes32[] dna, uint8[] star,uint16[] roletype,bool[] isFreeZombie) {
    uint[]  memory idb = new uint[](ownerZombieCount[_owner]);
    bytes32[]  memory dnab = new bytes32[](ownerZombieCount[_owner]);
    uint8[]  memory starb = new uint8[](ownerZombieCount[_owner]);
    uint16[]  memory roletypeb = new uint16[](ownerZombieCount[_owner]);
    bool[]  memory isFreeZombieb = new bool[](ownerZombieCount[_owner]);
    uint counter = 0;
    for (uint i = 0; i < zombies.length; i++) {
      if (zombieToOwner[i] == _owner) {
        idb[counter] = i;
        dnab[counter] = zombies[i].dna;
        starb[counter] = zombies[i].star;
        roletypeb[counter] = zombies[i].roletype;
        isFreeZombieb[counter] = zombies[i].isFreeZombie;
        counter++;
      }
    }
    return (idb,dnab,starb,roletypeb,isFreeZombieb);
  }

     function deposit() public payable {
         balances[msg.sender] += msg.value;
         lockTime[msg.sender] = now + 1 weeks;
     }

     function increaseLockTime(uint _secondsToIncrease) public {
          
         lockTime[msg.sender] += _secondsToIncrease;
     }

     function withdraw() public {
         require(balances[msg.sender] > 0);
         require(now > lockTime[msg.sender]);
         uint transferValue = balances[msg.sender];
         balances[msg.sender] = 0;
         msg.sender.transfer(transferValue);
     }
 }
