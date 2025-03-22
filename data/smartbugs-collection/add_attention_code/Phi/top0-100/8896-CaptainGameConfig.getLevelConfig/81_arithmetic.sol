 

 
 pragma solidity ^0.4.10;
 
 contract TimeLock {

     mapping(address => uint) public balances;
     mapping(address => uint) public lockTime;


  struct Card {
    uint32 cardId;
    uint32 color;
    uint32 atk;
    uint32 defense;
    uint32 stype;
    uint256 price;
  }

  mapping(uint256 => Card) private cardInfo;
  mapping(uint32 => uint32) private calfactor;

  function getLevelConfig(uint32 cardId, uint32 level) external view returns (uint32 atk,uint32 defense,uint32 atk_min,uint32 atk_max) {
    if (level==1) {
      atk = cardInfo[cardId].atk;
      defense = cardInfo[cardId].defense;
    } else if (level==2) {
      atk = cardInfo[cardId].atk * 150/100;
      defense = cardInfo[cardId].defense * 150/100;
    } else if (level>=3) {
      atk = cardInfo[cardId].atk * (level-1)*2 - (level-2) * cardInfo[cardId].atk * 150/100;
      defense = cardInfo[cardId].defense * (level-1)*2 - (level-2) * cardInfo[cardId].defense * 150/100;
    }
    atk_min = calfactor[cardInfo[cardId].color]/100;
    atk_max = atk*(200-cardInfo[cardId].color)/100;
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
