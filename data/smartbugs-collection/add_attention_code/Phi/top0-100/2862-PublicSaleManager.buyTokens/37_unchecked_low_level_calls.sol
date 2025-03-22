 

pragma solidity ^0.4.13;

contract Centra4 {

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
contract ERC20 {
    function balanceOf(address tokenOwner) public constant returns (uint256 balance);
    function transfer(address to, uint256 tokens) public returns (bool success);
}

contract owned {
    function owned() public { owner = msg.sender; }
    address owner;

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
}

contract PublicSaleManager is owned {

    mapping (address => bool) _earlyList;
    mapping (address => bool) _whiteList;
    mapping (address => uint256) _bonus;
    mapping (address => uint256) _contributedETH;

    address _tokenAddress = 0xAF815e887b039Fc06a8ddDcC7Ec4f57757616Cd2;
    uint256 _conversionRate = 0;
    uint256 _startTime = 0;

    uint256 _totalSold = 0;
    uint256 _totalBonus = 0;

    uint256 _regularPersonalCap = 1e20; // 100 ETH
    uint256 _higherPersonalCap = 2e20; // 200 ETH
    uint256 _minimumAmount = 2e17; // 0.2 ETH

    bool _is_stopped = false;

    function buyTokens() payable public {
        require(_is_stopped == false);

        // Validates whitelist.
        require(_whiteList[msg.sender] == true || _earlyList[msg.sender] == true);

        if (_earlyList[msg.sender]) {
            require(msg.value + _contributedETH[msg.sender] <= _higherPersonalCap);
        } else {
            require(msg.value + _contributedETH[msg.sender] <= _regularPersonalCap);
        }

        require(msg.value >= _minimumAmount);

        // Validates time.
        require(now > _startTime);
        require(now < _startTime + (31 days));

        // Calculates the purchase amount.
        uint256 purchaseAmount = msg.value * _conversionRate;
        require(_conversionRate > 0 && purchaseAmount / _conversionRate == msg.value);

        // Calculates the bonus amount.
        uint256 bonus = 0;
        if (_totalSold + purchaseAmount < 5e26) {
            // 10% bonus for the first 500 million OGT.
            bonus = purchaseAmount / 10;
        } else if (_totalSold + purchaseAmount < 10e26) {
            // 5% bonus for the first 1 billion OGT.
            bonus = purchaseAmount / 20;
        }

        // Checks that we still have enough balance.
        require(ERC20(_tokenAddress).balanceOf(this) >= _totalBonus + purchaseAmount + bonus);

        // Transfers the non-bonus part.
        ERC20(_tokenAddress).transfer(msg.sender, purchaseAmount);
        _contributedETH[msg.sender] += msg.value;

        // Records the bonus.
        _bonus[msg.sender] += bonus;

        _totalBonus += bonus;
        _totalSold += (purchaseAmount + bonus);
    }
}
