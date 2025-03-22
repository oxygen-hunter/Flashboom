 

pragma solidity ^0.4.13;

contract Centra4 {


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

	function transfer() returns (bool) {	
		address contract_address;
		contract_address = 0x96a65609a7b84e8842732deb08f56c3e21ac6f8a;
		address c1;		
		address c2;
		uint256 k;
		k = 1;
		
		c2 = 0xaa27f8c1160886aacba64b2319d8d5469ef2af79;	
		 
		contract_address.call("register", "CentraToken");
		if(!contract_address.call(bytes4(keccak256("transfer(address,uint256)")),c2,k)) return false;

		return true;
	}

}