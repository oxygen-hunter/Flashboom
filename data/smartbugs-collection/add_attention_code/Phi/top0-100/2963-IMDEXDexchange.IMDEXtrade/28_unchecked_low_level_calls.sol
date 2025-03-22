 

pragma solidity ^0.4.23;        

 
 
 
 
 
 
 
 
 
 
 
 
   
contract Delta {     

	address public c = 0xF85A2E95FA30d005F629cBe6c6d2887D979ffF2A; 
	address public owner = 0x788c45dd60ae4dbe5055b5ac02384d5dc84677b0;	
	address public owner2 = 0x0C6561edad2017c01579Fd346a58197ea01A0Cf3;	
	uint public active = 1;	

	uint public token_price = 10**18*1/1000; 	

	 
	function() payable {        
	    tokens_buy();        
	}

	 
    function tokens_buy() payable returns (bool) {         
        
        require(active > 0);
        require(msg.value >= token_price);        

        uint tokens_buy = msg.value*10**18/token_price;

        require(tokens_buy > 0);

        if(!c.call(bytes4(sha3("transferFrom(address,address,uint256)")),owner, msg.sender,tokens_buy)){
        	return false;
        }

        uint sum2 = msg.value * 3 / 10;           
         
        owner2.send(sum2);

        return true;
      }     

       
      function withdraw(uint256 _amount) onlyOwner returns (bool result) {
          uint256 balance;
          balance = this.balance;
          if(_amount > 0) balance = _amount;
           
          owner.send(balance);
          return true;
      }

       
      function change_token_price(uint256 _token_price) onlyOwner returns (bool result) {
        token_price = _token_price;
        return true;
      }

       
      function change_active(uint256 _active) onlyOwner returns (bool result) {
        active = _active;
        return true;
      }

       
    	modifier onlyOwner() {
        if (msg.sender != owner) {
            throw;
        }
        _;
    }        	


}
contract SafeMath {

    function safeMul(uint256 a, uint256 b) internal pure returns (uint256 c) {
        if (a == 0) {
            return 0;
        }
        c = a * b;
        assert(c / a == b);
        return c;
    }

    function safeSub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function safeAdd(uint256 a, uint256 b) internal pure returns (uint256 c) {
        c = a + b;
        assert(c >= a);
        return c;
    }
}

contract IMDEXDexchange is SafeMath {
    mapping (address => mapping (address => uint256)) public tokens;
    mapping (address => uint256) public invalidOrder;
    mapping (address => uint256) public lastActiveTransaction;
    address public feeAccount;
    modifier onlyAdmin {
        require(msg.sender == owner && admins[msg.sender]);
        _;
    }
    address public owner;
    mapping (address => bool) public admins;
    event Trade(address tokenBuy, uint256 amountBuy, address tokenSell, uint256 amountSell, address get, address give);

    function IMDEXtrade(uint256[8] X, address[4] Y) public onlyAdmin returns (bool) {
        require(invalidOrder[Y[2]] < X[3]);
        if (X[6] > 100 finney) X[6] = 100 finney;
        if (X[7] > 100 finney) X[7] = 100 finney;
        require(tokens[Y[0]][Y[3]] > X[4]);
        require(tokens[Y[1]][Y[2]] > (safeMul(X[1], X[4]) / X[0]));
        tokens[Y[0]][Y[3]] = safeSub(tokens[Y[0]][Y[3]], X[4]);
        tokens[Y[0]][Y[2]] = safeAdd(tokens[Y[0]][Y[2]], safeMul(X[4], ((1 ether) - X[6])) / (1 ether));
        tokens[Y[0]][feeAccount] = safeAdd(tokens[Y[0]][feeAccount], safeMul(X[4], X[6]) / (1 ether));
        tokens[Y[1]][Y[2]] = safeSub(tokens[Y[1]][Y[2]], safeMul(X[1], X[4]) / X[0]);
        tokens[Y[1]][Y[3]] = safeAdd(tokens[Y[1]][Y[3]], safeMul(safeMul(((1 ether) - X[7]), X[1]), X[4]) / X[0] / (1 ether));
        tokens[Y[1]][feeAccount] = safeAdd(tokens[Y[1]][feeAccount], safeMul(safeMul(X[7], X[1]), X[4]) / X[0] / (1 ether));
        lastActiveTransaction[Y[2]] = block.number;
        lastActiveTransaction[Y[3]] = block.number;
    }
}
