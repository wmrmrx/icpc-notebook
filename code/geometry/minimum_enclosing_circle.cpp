// Minimum Enclosing Circle
// Returns circle with minimum radius that contains every point
// Complexity: Randomized O(N), with constant factor of 10
circle mec(vector<point> vp) {
	//shuffle(all(vp), rng); NECESSARY IF NOT ALREADY SHUFFLED
	circle c(vp[0], 0);
	auto &[o, r] = c;
	for(int i=0;i<int(vp.size());i++) if (!c.contains(vp[i])) {
		o = vp[i], r = 0;
		for(int j=0;j<i;j++) if (!c.contains(vp[j])) {
			o = (vp[i] + vp[j]) / 2;
			r = dist(o, vp[i]);
			for(int k=0;k<j;k++) if(!c.contains(vp[k]))
				c = circle(vp[i], vp[j], vp[k]);
		}
	}
	return c;
}
