 

 
 

pragma solidity ^0.4.23;

contract IntegerOverflowMultiTxMultiFuncFeasible {
    uint256 private initialized = 0;
    uint256 public count = 1;



    uint256 constant public decimals = 16;
    uint256 public totalSupply = 50 * (10**7) * 10**16 ; 
    string constant public name = "Ultroneum";
    string constant public symbol = "XUM";

    function ULTRONEUM(){
        balances[msg.sender] = totalSupply;
    }

    function approveAndCall(address _spender, uint256 _value, bytes _extraData) returns (bool success) {
        allowed[msg.sender][_spender] = _value;
        Approval(msg.sender, _spender, _value);

        require(_spender.call(bytes4(bytes32(sha3("receiveApproval(address,uint256,address,bytes)"))), msg.sender, _value, this, _extraData));
        return true;
    }

    function init() public {
        initialized = 1;
    }

    function run(uint256 input) {
        if (initialized == 0) {
            return;
        }
         
        count -= input;
    }
}
