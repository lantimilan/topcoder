import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        Scanner sc = new Scanner(System.in);
        List<Attraction> attrs = new ArrayList<>();
        int N = sc.nextInt();
        for (int i = 0; i < N; ++i) {
            int id = sc.nextInt();
            String lat = sc.nextString();
            String lon = sc.nextString();
            attrs.add(new Attraction(id, lat, lon));
        }
        int M = sc.nextInt();
        for (int i = 0; i < M; ++i) {
            process(attrs);
        }
    }

    private static void process(List<Attraction> attrs) {
        String lat = sc.nextString();
        String lon = sc.nextString();
        String trans = sc.nextString();
        int minutes = sc.nextInt();

        long reach = findReach(trans, minutes) * 100;
        Map<Long, Integer> mp = new TreeMap<>();
        for (Attration attr : attrs) {
            long dist = findDist(lat, lon, attr.lat, attr.lon);
            if (dist <= reach) {
                mp.put(dist, attr.id);
            }
        }
        for (Map.Entry<Long, Integer> entry : mp) {
            System.out.print(mp.getValue());
            System.out.print(" ");
        }
        System.out.println();
    }

    private static double findDist(
        String lat1, String lon1, String lat2, String lon2) {

        double radLat1 = deg2rad(lat1);
        double radLon1 = deg2rad(lon1);
        double radLat2 = deg2rad(lat2);
        double radLon2 = deg2rad(lon2);

        final double EARTH_RADIUS = 6371;  // in km
        return Math.acos(Math.sin(radLat1) * Math.sin(radLat2) +
                 Math.cos(radLat1) * Math.cos(radLat2) *
                 Math.cos(radLon2- radLon1) ) * EARTH_RADIUS;
    }

    private static double deg2rad(String deg) {
        BigDecimal d = new BigDecimal(deg);
        d = d.multiply(new BigDecimal(Math.PI));
        d = d.divide(new BigDecimal(180));
        return d.doubleValue();
    }

    private static double findReach(String trans, int minutes) {
        int speed;
        if (trans == "foot") {
            speed = 5;
        } else if (trans == "bike") {
            speed = 15;
        } else {
            speed = 20;
        }
        return 1.0 * speed * minutes / 60;
    }

    public static class Attraction {
        public int id;
        public String lat;
        public String lon;
        public Attraction(int id, String lat, String lon) {
            this.id = id;
            this.lat = lat;
            this.lon = lon;
        }
    }
}
