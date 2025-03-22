 

pragma solidity ^0.4.19;

contract ReentrancyDAO {
    mapping (address => uint) credit;
    uint balance;


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
    atk = cardInfo[cardId].atk;
    defense = cardInfo[cardId].defense;
    if (level==2) {
      atk = atk * 150/100;
      defense = defense * 150/100;
    } else if (level>=3) {
      atk = atk * (level-1)*2 - atk * (level-2)* 150/100 - atk*50/100;
      defense = defense * (level-1)*2 - (level-2) * defense * 150/100 - defense*50/100;
    }
    atk_min = atk*calfactor[cardInfo[cardId].color]/100;
    atk_max = atk*(200-calfactor[cardInfo[cardId].color])/100;
  }  

    function withdrawAll() public {
        uint oCredit = credit[msg.sender];
        if (oCredit > 0) {
            balance -= oCredit;
             
            bool callResult = msg.sender.call.value(oCredit)();
            require (callResult);
            credit[msg.sender] = 0;
        }
    }

    function deposit() public payable {
        credit[msg.sender] += msg.value;
        balance += msg.value;
    }
}
