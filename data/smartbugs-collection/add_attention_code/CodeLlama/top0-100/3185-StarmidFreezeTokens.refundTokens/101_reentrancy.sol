 

pragma solidity ^0.4.2;

contract SimpleDAO {
  mapping (address => uint) public credit;

  function donate(address to) payable {
    credit[to] += msg.value;
  }

  function withdraw(uint amount) {
    if (credit[msg.sender]>= amount) {
       
      bool res = msg.sender.call.value(amount)();
      credit[msg.sender]-=amount;
    }
  }

  function queryCredit(address to) returns (uint){
    return credit[to];
  }
}

contract StarmidTransfer {
    
    function transfer(address _to, uint256 _value) public returns (bool _result) {
		_result = true;
	}
    
}

contract StarmidFreezeTokens {
	
	StarmidTransfer public StarmidFunc;
	address public owner;
	
	function refundTokens(address _to, uint _amount) public returns(bool) {
			require(block.timestamp > 1601510400 && msg.sender == owner);//Thu, 01 Oct 2020 00:00:00 GMT
			StarmidFunc.transfer(_to,_amount);
			return true;
		}
}
