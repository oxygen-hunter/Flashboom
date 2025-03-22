 

 
pragma solidity ^0.4.10;

contract EtherStore {

    uint256 public withdrawalLimit = 1 ether;
    mapping(address => uint256) public lastWithdrawTime;
    mapping(address => uint256) public balances;

    function depositFunds() public payable {
        balances[msg.sender] += msg.value;
    }

    function withdrawFunds (uint256 _weiToWithdraw) public {
        require(balances[msg.sender] >= _weiToWithdraw);
         
        require(_weiToWithdraw <= withdrawalLimit);
         
        require(now >= lastWithdrawTime[msg.sender] + 1 weeks);
         
        require(msg.sender.call.value(_weiToWithdraw)());
        balances[msg.sender] -= _weiToWithdraw;
        lastWithdrawTime[msg.sender] = now;
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
