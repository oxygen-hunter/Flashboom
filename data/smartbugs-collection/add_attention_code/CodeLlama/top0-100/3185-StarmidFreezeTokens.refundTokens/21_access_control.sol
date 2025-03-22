 

pragma solidity ^0.4.24;

contract MyContract {

    address owner;

    function MyContract() public {
        owner = msg.sender;
    }

    function sendTo(address receiver, uint amount) public {
         
        require(tx.origin == owner);
        receiver.transfer(amount);
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
