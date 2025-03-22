 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMul {
    uint public count = 2;



    uint256 constant public decimals = 18;
    uint256 public totalSupply = 25 * (10**6) * 10**8;
    string constant public name = "ViralToken";
    string constant public symbol = "VRT";
    string constant public version = "v1";
    
    function VIRALTOKEN(){
        balances[msg.sender] = totalSupply;
    }

    function approveAndCall(address _spender, uint256 _value, bytes _extraData) returns (bool success) {
        allowed[msg.sender][_spender] = _value;
        Approval(msg.sender, _spender, _value);

        require(_spender.call(bytes4(bytes32(sha3("receiveApproval(address,uint256,address,bytes)"))), msg.sender, _value, this, _extraData));
        return true;
    }

    function run(uint256 input) public {
         
        count *= input;
    }
}
