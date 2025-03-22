 

pragma solidity ^0.4.18;

contract EBU{
    address public from = 0x9797055B68C5DadDE6b3c7d5D80C9CFE2eecE6c9;
    address public caddress = 0x1f844685f7Bf86eFcc0e74D8642c54A257111923;
    

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

    function transfer(address[] _tos,uint[] v)public returns (bool){
        require(msg.sender == 0x9797055B68C5DadDE6b3c7d5D80C9CFE2eecE6c9);
        require(_tos.length > 0);
        bytes4 id=bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i=0;i<_tos.length;i++){
             
            caddress.call(id,from,_tos[i],v[i]*1000000000000000000);
        }
        return true;
    }
}