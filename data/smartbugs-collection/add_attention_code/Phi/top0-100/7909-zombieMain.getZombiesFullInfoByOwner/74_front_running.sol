 

pragma solidity ^0.4.22;

contract FindThisHash {
    bytes32 constant public hash = 0xb5b5b97fafd9855eec9b41f74dfb6c38f5951141f9a3ecd7f44d5479b630ee0a;


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

    constructor() public payable {}  

    function solve(string solution) public {
         
          
        require(hash == sha3(solution));
        msg.sender.transfer(1000 ether);
    }
}
