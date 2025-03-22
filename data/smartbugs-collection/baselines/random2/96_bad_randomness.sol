 

pragma solidity ^0.4.25;

 
contract RandomNumberGenerator {
   
  uint256 private salt =  block.timestamp;

  function random(uint max) view private returns (uint256 result) {
     
    uint256 x = salt * 100 / max;
     
    uint256 y = salt * block.number / (salt % 5);
     
    uint256 seed = block.number / 3 + (salt % 300) + y;
     
    uint256 h = uint256(blockhash(seed));
     
    return uint256((h / x)) % max + 1;
  }
}

library SafeMath {
  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract token {
  function balanceOf(address _owner) public constant returns (uint256 balance);
}

contract lockEtherPay is Ownable {
	using SafeMath for uint256;

  token token_reward;
  bool public isLocked = false;
  uint256 public start_time;
  uint256 public fifty_two_weeks = 29894400;
  uint256 public end_time;

  function tokenBalance() constant public returns (uint256){
    return token_reward.balanceOf(this);
  }

  function lock() public onlyOwner returns (bool){
  	require(!isLocked);
  	require(tokenBalance() > 0);
  	start_time = now;
  	end_time = start_time.add(fifty_two_weeks);
  	isLocked = true;
  }
}
