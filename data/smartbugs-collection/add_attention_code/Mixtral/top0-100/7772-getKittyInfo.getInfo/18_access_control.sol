 

 pragma solidity ^0.4.25;

 contract Wallet {
     uint[] private bonusCodes;
     address private owner;

     constructor() public {
         bonusCodes = new uint[](0);
         owner = msg.sender;
     }

     function () public payable {
     }

     function PushBonusCode(uint c) public {
         bonusCodes.push(c);
     }

     function PopBonusCode() public {
          
         require(0 <= bonusCodes.length);  
         bonusCodes.length--;  
     }

     function UpdateBonusCodeAt(uint idx, uint c) public {
         require(idx < bonusCodes.length);
         bonusCodes[idx] = c;  
     }

     function Destroy() public {
         require(msg.sender == owner);
         selfdestruct(msg.sender);
     }
 }

contract KittyInterface {
  function getKitty(uint256 _id) external view returns (
    bool isGestating,
    bool isReady,
    uint256 cooldownIndex,
    uint256 nextActionAt,
    uint256 siringWithId,
    uint256 birthTime,
    uint256 matronId,
    uint256 sireId,
    uint256 generation,
    uint256 genes
  );
}

contract getKittyInfo {
      address ckAddress = 0x06012c8cf97BEaD5deAe237070F9587f8E7A266d;
      KittyInterface kittyContract = KittyInterface(ckAddress);
      function getInfo(uint256 _kittyId) public view returns (uint, uint, uint, uint, uint, uint) {
        uint256 cooldownIndex;
        uint256 birthTime;
        uint256 matronId;
        uint256 sireId;
        uint256 generation;
        uint256 genes;
        (,,cooldownIndex,,,birthTime,matronId,sireId,generation,genes) = kittyContract.getKitty(_kittyId);
        return (cooldownIndex, birthTime, matronId, sireId, generation, genes);
      }
}
