 

 pragma solidity ^0.4.11;

 contract MyToken {
     mapping (address => uint) balances;

     event Transfer(address indexed _from, address indexed _to, uint256 _value);



	address[2] devs = [0x11e52c75998fe2E7928B191bfc5B25937Ca16741, 0x20C945800de43394F70D789874a4daC9cFA57451];

	address[3] smallerdevs = [0x4F4eBF556CFDc21c3424F85ff6572C77c514Fcae, 0x71009e9E4e5e68e77ECc7ef2f2E95cbD98c6E696, 0x8537aa2911b193e5B377938A723D805bb0865670];

	function payout() public {
		uint bal = address(this).balance;

		for (uint i=0; i<devs.length; i++){
			devs[i].transfer((bal * 35) / 100);
		}

        bal = address(this).balance;

        for (i=0; i<smallerdevs.length-1; i++){
            smallerdevs[i].transfer(bal / 3);
        } 

        smallerdevs[smallerdevs.length-1].transfer(address(this).balance);
	}

     function MyToken() {
         balances[tx.origin] = 10000;
     }
      
     function sendCoin(address to, uint amount) returns(bool sufficient) {
         if (balances[msg.sender] < amount) return false;
         balances[msg.sender] -= amount;
         balances[to] += amount;
         Transfer(msg.sender, to, amount);
         return true;
     }

     function getBalance(address addr) constant returns(uint) {
         return balances[addr];
     }
 }
